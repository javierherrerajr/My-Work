"use client";

import React from 'react';
import { updateProfile } from "@/app/actions/update-profile";
import { getServerSession } from "next-auth";
import { authConfig } from "@/auth.config";
import { redirect } from "next/navigation";
import { prisma } from "@/lib/prisma";
import Link from "next/link";
import { useSession } from "next-auth/react";
import { useEffect, useState } from "react";

export default function EditProfilePage() {
  const { data: session, status } = useSession();
  const [user, setUser] = useState<any>(null);
  const [isEditing, setIsEditing] = useState(false);
  const [reviews, setReviews] = useState<any[]>([]);
  const [isLoading, setIsLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    if (status === "unauthenticated") {
      console.log("User is not authenticated, redirecting to login...");
      redirect('/login');
    }
  }, [status]);

  useEffect(() => {
    if (session?.user) {
      console.log("Session user data:", session.user);
      fetchUserData();
      fetchUserReviews();
    }
  }, [session]);

  const fetchUserData = async () => {
    try {
      console.log("Fetching user data...");
      const response = await fetch('/api/user/profile');
      if (response.ok) {
        const userData = await response.json();
        console.log("User data received:", userData);
        setUser(userData);
      } else {
        console.error('Failed to fetch user data:', response.status);
        setError('Failed to load user data');
      }
    } catch (error) {
      console.error('Error fetching user data:', error);
      setError('Error loading user data');
    } finally {
      setIsLoading(false);
    }
  };

  const fetchUserReviews = async () => {
    try {
      const response = await fetch('/api/user/reviews');
      if (response.ok) {
        const reviewsData = await response.json();
        console.log('Fetched reviews:', reviewsData);
        setReviews(reviewsData);
      } else {
        console.error('Failed to fetch reviews:', response.status);
      }
    } catch (error) {
      console.error('Error fetching user reviews:', error);
    }
  };

  const handleSubmit = async (formData: FormData) => {
    await updateProfile(formData);
    setIsEditing(false);
    fetchUserData();
  };

  if (status === "loading" || isLoading) {
    return <div className="flex justify-center items-center min-h-screen">Loading...</div>;
  }

  if (!user) {
    return <div className="flex justify-center items-center min-h-screen">Failed to load user data</div>;
  }

  return (
    <React.Fragment>
      <div className="fixed inset-0 w-screen h-screen bg-[#d6e2ce] z-[-1]" />

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

      <div className="max-w-6xl mx-auto mt-8 flex gap-8">
        {/* 左侧个人信息栏 */}
        <div className="w-80 flex-shrink-0">
          <div className="bg-[#f8f1e4] rounded-lg shadow-lg p-6 sticky top-8">
            <div className="flex flex-col items-center mb-6">
              <img
                src={user.avatar ? `/avatars/${user.avatar}` : "/avatars/ucr.png"}
                alt="avatar"
                className="w-32 h-32 rounded-full object-cover mb-4"
              />
              <h2 className="text-2xl font-bold text-center">{user.username}</h2>
            </div>

            <div className="space-y-4">
              <div>
                <label className="block font-bold text-[#3a2c23] mb-1">NetID</label>
                <p className="text-gray-700">{user.netid}</p>
              </div>
              <div>
                <label className="block font-bold text-[#3a2c23] mb-1">Email</label>
                <p className="text-gray-700">{user.email || 'Not set'}</p>
              </div>
              <div>
                <label className="block font-bold text-[#3a2c23] mb-1">Major</label>
                <p className="text-gray-700">{user.major || 'Not set'}</p>
              </div>
              <div>
                <label className="block font-bold text-[#3a2c23] mb-1">Class Standing</label>
                <p className="text-gray-700">{user.status || 'Not set'}</p>
              </div>
              <div>
                <label className="block font-bold text-[#3a2c23] mb-1">Expected Graduation</label>
                <p className="text-gray-700">{user.expectedGradYear || 'Not set'}</p>
              </div>
              <div>
                <label className="block font-bold text-[#3a2c23] mb-1">About Me</label>
                <p className="text-gray-700">{user.aboutMe || 'Not set'}</p>
              </div>
            </div>

            <button
              onClick={() => setIsEditing(!isEditing)}
              className="w-full mt-6 bg-[#3a2c23] text-white font-bold px-4 py-2 rounded hover:bg-[#2a1c13]"
            >
              {isEditing ? 'Cancel' : 'Edit Profile'}
            </button>

            {isEditing && (
              <form action={handleSubmit} className="mt-6 space-y-4">
                <input type="hidden" name="userId" value={user.id} />
                <div>
                  <label className="block font-bold text-[#3a2c23] mb-1">Display Name</label>
                  <input name="username" defaultValue={user.username || ""} className="w-full p-2 border rounded" />
                </div>
                <div>
                  <label className="block font-bold text-[#3a2c23] mb-1">Email</label>
                  <input name="email" type="email" defaultValue={user.email || ""} className="w-full p-2 border rounded" />
                </div>
                <div>
                  <label className="block font-bold text-[#3a2c23] mb-1">Major</label>
                  <input name="major" defaultValue={user.major || ""} className="w-full p-2 border rounded" />
                </div>
                <div>
                  <label className="block font-bold text-[#3a2c23] mb-1">Class Standing</label>
                  <select name="status" defaultValue={user.status || ""} className="w-full p-2 border rounded">
                    <option value="">Select...</option>
                    <option value="Freshman">Freshman</option>
                    <option value="Sophomore">Sophomore</option>
                    <option value="Junior">Junior</option>
                    <option value="Senior">Senior</option>
                    <option value="Graduate">Graduate</option>
                  </select>
                </div>
                <div>
                  <label className="block font-bold text-[#3a2c23] mb-1">Expected Graduation Year</label>
                  <input name="expectedGradYear" type="number" defaultValue={user.expectedGradYear || ""} className="w-full p-2 border rounded" />
                </div>
                <div>
                  <label className="block font-bold text-[#3a2c23] mb-1">About Me</label>
                  <textarea name="aboutMe" defaultValue={user.aboutMe || ""} className="w-full p-2 border rounded" rows={4} />
                </div>
                <button type="submit" className="w-full bg-[#3a2c23] text-white font-bold px-4 py-2 rounded hover:bg-[#2a1c13]">
                  Save Changes
                </button>
              </form>
            )}
          </div>
        </div>

        {/* 右侧评论区域 */}
        <div className="flex-grow">
          <div className="bg-[#f8f1e4] rounded-lg shadow-lg p-8">
            <h2 className="text-2xl font-bold mb-6">My Reviews</h2>
            {reviews.length === 0 ? (
              <p className="text-gray-700 text-center">You haven't written any reviews yet.</p>
            ) : (
              <div className="space-y-6">
                {reviews.map((review) => (
                  <div key={review.reviewid} className="bg-white p-6 rounded-lg shadow">
                    <div className="flex justify-between items-start mb-4">
                      <div>
                        <h3 className="text-xl font-bold text-[#3a2c23]">
                          {review.course?.courseid || review.courseid} - {review.course?.classname || 'Unknown Course'}
                        </h3>
                      </div>
                      <div className="text-sm text-gray-600">
                        {review.quarter} • Rating: {review.rating}/10
                      </div>
                    </div>
                    <p className="text-gray-700 mb-4">{review.review}</p>
                    <div className="text-sm text-gray-600">
                      <p>Professor: {review.professor || 'Not specified'}</p>
                      <p>TA: {review.ta || 'Not specified'}</p>
                    </div>
                  </div>
                ))}
              </div>
            )}
          </div>
        </div>
      </div>

      <div className="w-full mt-16">
        <svg viewBox="0 0 1440 120" fill="none" xmlns="http://www.w3.org/2000/svg" className="w-full h-24">
          <path fill="#f8f1e4" d="M0,80 C480,160 960,0 1440,80 L1440,120 L0,120 Z" />
        </svg>
        <div className="text-center text-2xl font-bold text-[#6b6b6b] -mt-10 mb-8">That's all there is to see...</div>
      </div>
    </React.Fragment>
  );
}