"use client";

import { getServerSession } from "next-auth";
import { authConfig } from "@/auth.config";
import { prisma } from "@/lib/prisma";
import { notFound } from "next/navigation";
import Link from "next/link";

interface PageProps {
  params: {
    userID: string;
  };
}

export default async function UserProfilePage({ params }: PageProps) {
  const session = await getServerSession(authConfig);
  
  if (!session?.user?.id && !session?.user?.netid) {
    return notFound();
  }

  const user = await prisma.user.findFirst({
    where: {
      OR: [
        { id: session.user.id },
        { netid: session.user.netid }
      ]
    }
  });

  if (!user) {
    return notFound();
  }

  const reviews = await prisma.review.findMany({
    where: {
      OR: [
        { userId: user.id },
        { netid: user.netid }
      ]
    },
    include: {
      course: {
        select: {
          courseid: true,
          classname: true
        }
      }
    },
    orderBy: {
      reviewid: 'desc'
    }
  });

  return (
    <>
      {/* Green background */}
      <div className="fixed inset-0 w-screen h-screen bg-[#d6e2ce] z-[-1]" />

      {/* Top bar and logo */}
      <div className="relative w-screen flex items-center pt-6 pb-6 left-1/2 right-1/2 -translate-x-1/2">
        <div className="absolute left-0 top-1/2 -translate-y-1/2 h-12 w-full bg-[#f8f1e4] rounded-r-lg z-0" />
        <div className="relative z-10 w-28 h-28 rounded-full border-4 border-[#f8f1e4] overflow-hidden flex items-center justify-center ml-8">
          <Link href="/home">
            <img
              src="/bearlogo.svg"
              alt="logo"
              className="w-full h-full object-cover rounded-full"
            />
          </Link>
        </div>
      </div>

      {/* Profile display */}
      <div className="flex flex-row max-w-6xl mx-auto mt-8 gap-8">
        <div className="bg-[#f8f1e4] rounded-lg shadow-lg p-8 flex flex-col items-center w-80">
          <img
            src={user.avatar ? `/avatars/${user.avatar}` : "/avatars/ucr.png"}
            alt="avatar"
            className="w-32 h-32 rounded-full object-cover mb-4"
          />
          <div className="text-2xl font-bold mb-2">{user.username || user.netid}</div>
          <div className="w-full border-t border-[#d6e2ce] my-2" />
          <div className="w-full text-center py-2">{user.netid}</div>
          <div className="w-full border-t border-[#d6e2ce] my-2" />
          <div className="w-full text-center py-2">Year: {user.status}</div>
          <div className="w-full border-t border-[#d6e2ce] my-2" />
          <div className="w-full text-center py-2">Class of {user.expectedGradYear}</div>
        </div>

        <div className="flex-1">
          <h2 className="text-2xl font-bold mb-6">Reviews by {user.username || user.netid}</h2>
          {reviews.length === 0 ? (
            <p className="text-gray-600 text-center">This user hasn't submitted any reviews yet.</p>
          ) : (
            <ul className="space-y-4">
              {reviews.map((review) => (
                <li key={review.reviewid} className="bg-white p-4 rounded shadow border border-gray-200">
                  <div className="text-lg font-semibold text-[#3a2c23]">{review.course?.classname || review.courseid}</div>
                  <p className="text-sm text-gray-700 mt-2">Rating: {review.rating} / Quarter: {review.quarter}</p>
                  <div className="text-sm text-gray-500">Instructor: {review.professor || 'Not specified'} | TA: {review.ta || 'Not specified'}</div>
                  <div className="mt-2 text-gray-700">{review.review}</div>
                </li>
              ))}
            </ul>
          )}
        </div>
      </div>

      {/* Footer */}
      <div className="w-full mt-16">
        <svg viewBox="0 0 1440 120" fill="none" xmlns="http://www.w3.org/2000/svg" className="w-full h-24">
          <path fill="#f8f1e4" d="M0,80 C480,160 960,0 1440,80 L1440,120 L0,120 Z" />
        </svg>
        <div className="text-center text-2xl font-bold text-[#6b6b6b] -mt-10 mb-8">Thanks for visiting this profile!</div>
      </div>
    </>
  );
}
