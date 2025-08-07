// app/courses/[courseId]/page.tsx
import React from 'react';
import { CourseInfoPanel } from "@/components/CourseInfoPanel";
import { ReviewCard } from "@/components/ReviewCard";
import { ReviewButton } from "@/components/ReviewButton";
import { prisma } from "@/lib/prisma";
import { notFound } from "next/navigation";
import Header from '@/components/Header'
import Footer from '@/components/Footer'

export default async function CourseDetailPage({
  params,
}: {
  params: Promise<{ courseId: string }>;
}) {
  const { courseId } = await params;

  // Find the course using courseid (which is the primary key)
  const course = await prisma.class.findUnique({
    where: { courseid: courseId }, // Use courseId from params and courseid field from schema
  });

  if (!course) return notFound();

  // Get reviews for this course
  const reviews = await prisma.review.findMany({
    where: { courseid: course.courseid },
    include: {
      user: {
        select: {
          id: true, // Assuming you might need user ID for some reason
          username: true,
        },
      },
    },
    orderBy: {
      reviewid: 'desc',
    },
  });

  // Calculate average rating (max 10, since reviews can be 1-5, we scale to 1-10)
  const averageRating = reviews.length > 0 
    ? reviews.reduce((acc, review) => acc + review.rating, 0) / reviews.length
    : 0;
  
  // Note: Your schema doesn't have a difficulty field in Review, using rating for now
  const averageDifficulty = reviews.length > 0
    ? Math.round((reviews.reduce((acc, review) => acc + review.rating, 0) / reviews.length) * 2) / 2
    : 0;

  return (
    <>
      <Header/>
      <div className="space-y-6 py-12 mt-5">
        <CourseInfoPanel course={{
          id: course.courseid,
          name: course.classname,
          subject: course.subject || '',
          department: course.subject?.split(' ')[0] || '',
          averageRating: averageRating,
          difficulty: averageDifficulty,
          passRate: 0, // TODO: Calculate from reviews if you add this field
        }} />
        
        <div className="flex justify-center">
          <ReviewButton courseId={course.courseid}/>
        </div>
        
        <div className="space-y-4">
          {reviews.length === 0 ? (
            <p className="text-gray-500 text-xl text-center py-12 font-semibold">
              No reviews yet. Be the first to review this course!
            </p>
          ) : (
            reviews.map((review) => (
              <div key={review.reviewid} className="px-12">
              <ReviewCard 
                key={review.reviewid} 
                review={{
                  id: review.reviewid.toString(),
                  difficulty: review.rating, // Using rating as difficulty since there's no separate difficulty field
                  quarter: review.quarter,
                  professor: review.professor,
                  ta: review.ta,
                  text: review.review,
                  user: { 
                    id: review.user.id,
                    username: review.user.username },
                  course: {
                    id: course.courseid,
                    name: course.classname,
                  },
                }} 
              />
              </div >
            ))
          )}
        </div>
      </div>
      <div className="mt-12">
        <Footer/>
      </div>
    </>
  );
}